
/**
  * UDUK
  * iherlambang@gmail.com
  * 
  * # gcc fftw.c -o fftw -lfftw3 -Wall -O2 -lsndfile
  * 
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fftw3.h>
#include <math.h>
#include <complex.h>
#include <sndfile.h>

double *
readWav (char *filename, long *len) {

  SF_INFO sndInfo_r;
  double *buffer_r;
  long numFrames;

  SNDFILE *sndFile_r = sf_open(filename, SFM_READ, &sndInfo_r);
  if (sndFile_r == NULL) {
    fprintf(stderr, "sf_open: '%s': %s\n", filename, sf_strerror(sndFile_r));
    exit(EXIT_FAILURE);
  }

  if (sndInfo_r.format != (SF_FORMAT_WAV | SF_FORMAT_PCM_16)) {
    fprintf(stderr, "Input should be 16bit Wav\n");
    sf_close(sndFile_r);
    exit(EXIT_FAILURE);
  }

  buffer_r = malloc((sndInfo_r.frames * sndInfo_r.channels) * sizeof(double));
  if (buffer_r == NULL) {
    fprintf(stderr, "malloc error\n");
    sf_close(sndFile_r);
    exit(EXIT_FAILURE);
  }

  numFrames = sf_readf_double(sndFile_r, buffer_r, sndInfo_r.frames * sndInfo_r.channels);
  if (numFrames != sndInfo_r.frames) {
    fprintf(stderr, "sf_readf_double problem\n");
    sf_close(sndFile_r);
    free(buffer_r);
    exit(EXIT_FAILURE);
  }

  if (sndInfo_r.channels == 2) {
    double *buffer_m = malloc((sndInfo_r.frames) * sizeof(double));

    for (int i = 0; i < sndInfo_r.frames; i++) {
      buffer_m[i] = 0;

      for(int j = 0; j < sndInfo_r.channels; j++) {
        buffer_m[i] += buffer_r[i * sndInfo_r.channels + j];
      }

      buffer_m[i] /= sndInfo_r.channels;
    }

    sf_close(sndFile_r);
    *len = numFrames;
    return buffer_m;
  }

  sf_close(sndFile_r);
  *len = numFrames;
  return buffer_r;
}

void
writeWav (char *filename, double *y, long numFrames) {

  SF_INFO info;
  info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
  info.channels = 1;
  info.samplerate = 44100;

  SNDFILE *sndFile = sf_open(filename, SFM_WRITE, &info);
  if (sndFile == NULL) {
    fprintf(stderr, "sfopen: '%s': %s\n", filename, sf_strerror(sndFile));
    exit(EXIT_FAILURE);
  }

  long writtenFrames = sf_writef_double(sndFile, (const double *) y, numFrames);

  if (writtenFrames != numFrames) {
    fprintf(stderr, "sf_writef_double problem\n");
    sf_close(sndFile);
    exit(EXIT_FAILURE);
  }

  sf_write_sync(sndFile);
  sf_close(sndFile);
}

void
frameProcessing (double *originalSignal, long originalLen)
{
  const int frameSize = 1024;
  double *frameSignal = (double *) calloc (frameSize, sizeof (double));

  double *out,*mag,*phase;
  double real,imag;

  // the 1st 1024 only -- 
  for (int i = 0; i < frameSize; i++) {
    frameSignal[i] = originalSignal[i];
  }

  fftw_complex *out_cpx, *mod_cpx;
  fftw_plan fft; 

  out_cpx = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(frameSize/2+1));
  mod_cpx = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(frameSize/2+1));
  out = (double *) malloc(frameSize*sizeof(double));
  mag = (double *) malloc(frameSize*sizeof(double));
  phase = (double *) malloc(frameSize*sizeof(double));

  fft = fftw_plan_dft_r2c_1d(frameSize, frameSignal, out_cpx, FFTW_ESTIMATE);
  fftw_execute(fft);
  
  #pragma omp parallel for
  for (int j = 0; j < frameSize/2 + 1; j++) {
    real = out_cpx[j][0];
    imag = out_cpx[j][1];
    mag[j] = sqrt((real*real)+(imag*imag));
    phase[j] = atan2(imag,real);
    printf("%.16f %.16f %.16f %.16f\n", real, imag, mag[j], phase[j]);
  }

  fftw_destroy_plan(fft);
  fftw_free(out_cpx);
  fftw_free(mod_cpx);
  free(out);
  free(mag);
  free(phase);
  free(frameSignal);
}

int 
main (int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s original.wav\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  long originalLen; 
  double *originalSignal = readWav(argv[1], 
      &originalLen);

  frameProcessing(originalSignal, originalLen);

  exit(EXIT_SUCCESS);;
}
