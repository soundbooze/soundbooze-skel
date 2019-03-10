let mic;
let amp;
let fft;

var hWindow;
var BENDING = 560.3; // avg'ed ...

function nuttall(N) {
  var TWOPI = Math.PI * 2;
     
  var a0 = 0.355768,
      a1 = 0.487396,
      a2 = 0.144232,
      a3 = 0.012604;
     
  var nuttallWindow = new Float32Array(N);
  
  for (let i = 0; i < N; i++) {
    var f = TWOPI*i/(N-1);
    nuttallWindow[i] = a0 - a1*Math.cos(f) +a2*Math.cos(2*f) - a3*Math.cos(3*f);
  }
  
  return nuttallWindow;
}

function zMax8(z) {
	var zs = z.slice(0);
	var s = zs.sort().reverse();
	var ret = [];
	for (var i = 0; i < 16; i++) {
	  ret.push(s[i]);
	}
	return ret;
}

function zMin8(z) {
	var zs = z.slice(0);
	var s = zs.sort();
	var c = [];
	
	for (var i = 0; i < s.length; i++) {
	  if (s[i] != 0) {
			c.push(s[i]);
		}
	}
	
	var ret = [];
	for (var i = 0; i < 16; i++) {
	  ret.push(c[i]);
	}
	return ret;
}

// https://derickbailey.com/2014/09/21/calculating-standard-deviation-with-array-map-and-array-reduce-in-javascript/

function standardDeviation(values){
  var avg = average(values);
  
  var squareDiffs = values.map(function(value){
    var diff = value - avg;
    var sqrDiff = diff * diff;
    return sqrDiff;
  });
  
  var avgSquareDiff = average(squareDiffs);

  var stdDev = Math.sqrt(avgSquareDiff);
  return stdDev;
}

function average(data){
  var sum = data.reduce(function(sum, value){
    return sum + value;
  }, 0);

  var avg = sum / data.length;
  return avg;
}

function setup() {
  createCanvas(500, 500);
  mic = new p5.AudioIn();
  mic.start();
  amp = new p5.Amplitude();
  amp.setInput(mic);
  fft = new p5.FFT();
  fft.setInput(mic);
  hWindow = nuttall(1024);
	console.clear();
}

var shredCoeff = [];
var shredCounter = 0;
var shredStd = 0;

function draw() {
	
  background(0);
	
  let bins = fft.analyze();
	
	var windowed = new Float32Array(bins.length);
	
  for (var i = 0; i < hWindow.length; i++) {
    windowed[i] = bins[i] * hWindow[i];    
  }
	
	var r8Max = zMax8(windowed);
	var r8MaxSum = 0;
	for (var j = 0; j < windowed.length; j++) {  
		stroke(222, 222, 0);
		line(j, height, j, height-windowed[j]);
  }

	shredStd = standardDeviation(r8Max);
	shredCoeff.push(shredStd);
	shredCounter++;
	if (shredCounter > width) {
		shredCoeff = [];
	  shredCounter = 0;
		shredStd = 0;
	}
	
	stroke(177);
	fill(177);
	for (var k = 0; k < r8Max.length; k++) {
	  r8MaxSum += r8Max[k];
		rect(k*34+24, (height - r8Max[k]) - 21, 4, 4);
	}
	
	text(r8MaxSum, 20, 20);
	if (r8MaxSum >= BENDING)
		text('[Bending]', 40, 40);
}
