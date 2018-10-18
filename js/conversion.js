function ToneJSFreqtoMIDInote(freq) {

  var scaleIndexToNote = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"];

  var log = Math.log2(freq / 440.0);
  var noteNumber = Math.round(12 * log) + 57;
  var octave = Math.floor(noteNumber/12);

  if (octave < 0){
    noteNumber += -12 * octave;
  }

  var noteName = scaleIndexToNote[noteNumber % 12];
  return noteName + octave.toString();

}

function ToneJSMIDItoFreq (midi){
  return 440.0 * Math.pow(2, (midi - 69) / 12);
};

function ToneJSFreqtoMIDI (freq) {
  return 69 + Math.round(12 * Math.log2(freq / 440.0));
}

var b = ToneJSFreqtoMIDI(110);
var c = ToneJSMIDItoFreq(69);
var a = ToneJSFreqtoMIDInote(c);

console.log(c, a);
