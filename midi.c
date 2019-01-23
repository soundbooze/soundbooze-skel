/* gcc midi.c -o midi -lasound -Wall -O3 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <alsa/asoundlib.h>

snd_seq_t *seq;
snd_seq_event_t ev;

int port;
int dest_client = 129, dest_port = 0;

void send_ev() {
	snd_seq_ev_set_direct(&ev);
	snd_seq_ev_set_source(&ev, port);
	snd_seq_ev_set_dest(&ev, dest_client, dest_port);
	snd_seq_event_output(seq, &ev);
}

void note_on(int note) {
	snd_seq_ev_set_noteon(&ev, 0, note, 120);
	send_ev();
}

void note_off(int note) {
	snd_seq_ev_set_noteoff(&ev, 0, note, 120);
	send_ev();
}

int 
main (int argc, char ** argv) {

	if (snd_seq_open(&seq, "default", SND_SEQ_OPEN_OUTPUT, 0) < 0) {
		fprintf(stderr, "Error: snd_seq_open\n");
		return -1;
	}

	port = snd_seq_create_simple_port(seq, "trigger", SND_SEQ_PORT_CAP_READ, SND_SEQ_PORT_TYPE_MIDI_GENERIC | 
                                                  SND_SEQ_PORT_TYPE_APPLICATION);
	if (port < 0) {
		fprintf(stderr, "Error: snd_seq_create_simple_port\n");
		snd_seq_close(seq);
		return -1;
	}

	if (snd_seq_connect_to(seq, port, dest_client, dest_port) < 0) {
		fprintf(stderr, "Error: snd_seq_connect_to\n");
		snd_seq_close(seq);
		return -1;
	}

	note_on(60);

	snd_seq_drain_output(seq);
  /* usleep(3121); */

	note_off(60);

	snd_seq_drain_output(seq);
	usleep(3121);

	snd_seq_close(seq);

	return 0;
}
