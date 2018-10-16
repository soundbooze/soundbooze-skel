int
process (jack_nframes_t nframes, void *arg)
{
	jack_default_audio_sample_t *in, *out;
	
	in = jack_port_get_buffer (input_port, nframes);
	//out = jack_port_get_buffer (output_port, nframes);

  int i = 0;
  for (i = 0; i < sizeof(in)/sizeof(jack_default_audio_sample_t); i++) {
    printf("%.21f\n", in[i]);
  }

  //featureExtract(here);
  //waveShape(here);
  
	//memcpy (out, in, sizeof (jack_default_audio_sample_t) * nframes);

	return 0;      
}
