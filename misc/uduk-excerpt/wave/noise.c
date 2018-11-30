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
noise (long noiseLen)
{
  double *noiseSignal = (double *) calloc (noiseLen * 2, sizeof (double));

  int frequency = 432;

  #pragma omp for schedule(dynamic, CHUNKSIZE)
  for (long i = 0; i < noiseLen * 2; i++) {
    //noiseSignal[i] = sin(100 * (2 * M_PI) * i / 44100);
    noiseSignal[i] =  cos(100 * (2 * M_PI) * frequency * i / 44100);
  }

  return noiseSignal;
}

int 
main (int argc, char *argv[])
{

  if (argc != 2) {
    fprintf(stderr, "Usage: %s output.wav\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  long noiseLen = 44100 * 10;
  double *noiseSignal = noise (noiseLen);

  writeWav(argv[1], noiseSignal, noiseLen);

  free(noiseSignal);

  exit(EXIT_SUCCESS);;
}
