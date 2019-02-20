#define ALSA_PCM_NEW_HW_PARAMS_API

#include <alsa/asoundlib.h>

int main() {
  long loops;
  int rc;
  int size;
  snd_pcm_t *handle;
  snd_pcm_hw_params_t *params;
  unsigned int val;
  int dir;
  snd_pcm_uframes_t frames;
  int16_t *buffer_file;
  int16_t *buffer;
  
  rc = snd_pcm_open(&handle, "hw:0", SND_PCM_STREAM_PLAYBACK, 0);
  if (rc < 0) {
    fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
    exit(1);
  }
  
  snd_pcm_hw_params_alloca(&params);
  snd_pcm_hw_params_any(handle, params);
  snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
  snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
  snd_pcm_hw_params_set_channels(handle, params, 2);

  val = 44100;
  snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);

  frames = 32;
  snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

  rc = snd_pcm_hw_params(handle, params);
  if (rc < 0) {
    fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
    exit(1);
  }

  snd_pcm_hw_params_get_period_size(params, &frames, &dir);

  size = frames * 4; /* 2 bytes/sample, 2 channels */
  
  buffer_file = (int16_t *) malloc(frames * 2 * sizeof(int16_t));
  buffer = (int16_t *) malloc(size * sizeof(int16_t));

  snd_pcm_hw_params_get_period_time(params, &val, &dir);

  /* 5 seconds in microseconds divided by 
   * period time */
  loops = 5000000 / val;

  while (loops > 0) {
    loops--;
    rc = read(0, buffer_file, frames*2);
    if (rc == 0) {
      fprintf(stderr, "end of file on input\n");
      break;
    } else if (rc != frames*2) {
      fprintf(stderr, "short read: read %d bytes\n", rc);
    }

    register_t i = 0,j  = 0;
    for (i = 0; i < frames*2; i++, j+=2) {
      buffer[j] = buffer_file[i];
      buffer[j+1] = buffer_file[i];
    }

    rc = snd_pcm_writei(handle, buffer, frames);
    if (rc == -EPIPE) {
      fprintf(stderr, "underrun occurred\n");
      snd_pcm_prepare(handle);
    } else if (rc < 0) {
      fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
    }  else if (rc != (int)frames) {
      fprintf(stderr, "short write, write %d frames\n", rc);
    }
  }

  snd_pcm_drain(handle);
  snd_pcm_close(handle);
  free(buffer);
  
  return 0;
}
