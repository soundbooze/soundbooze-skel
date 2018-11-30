#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sndfile.h>

#define CHUNKSIZE 8

void
writeWav (char *filename, double *y, long numFrames) {

  SF_INFO info;
  info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
  info.channels = 2;
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

double *
sawtooth (long signalLen)
{
  double *sawtoothSignal = (double *) calloc (signalLen * 2, sizeof (double));

  int frequency = 432;
  int channels = 2;
  int period = 44100 / frequency;

  #pragma omp for schedule(dynamic, CHUNKSIZE)
  for (long i = 0; i < signalLen * 2; i++) {
    sawtoothSignal[i] = 2 * (i / channels % period) / (double) period - 1;
  }

  return sawtoothSignal;
}

int 
main (int argc, char *argv[])
{

  if (argc != 2) {
    fprintf(stderr, "Usage: %s output.wav\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  long signalLen = 44100 * 10;
  double *sawtoothSignal = sawtooth(signalLen);

  writeWav(argv[1], sawtoothSignal, signalLen);

  free(sawtoothSignal);

  exit(EXIT_SUCCESS);;
}
