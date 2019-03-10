let mic;
let amp;
let fft;

function setup() {
  createCanvas(400, 400);
  mic = new p5.AudioIn();
  mic.start();
  
  amp = new p5.Amplitude();
  amp.setInput(mic);
  
  fft = new p5.FFT();
  fft.setInput(mic);
}

function draw() {
  background(220);
  console.log(mic.getLevel());
  console.log(amp.getLevel());
  
  let bins = fft.analyze();
  
  for(let b in bins) {
   let bin = bins[b];
   line(b, height, b, height-bin); 
  }
}
