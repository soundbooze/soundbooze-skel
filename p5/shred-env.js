let mic;
let amp;
let fft;

var hWindow;

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

function e(buffer) {
    var attackTime =  0.0002;
    var releaseTime =  0.0004;
    var gainAttack ;
    var gainRelease;
    var envelopeOut = 0.0;
    
    var result = new Float32Array(buffer.length);
    
    gainAttack = Math.exp(-1.0/(sampleRate()*attackTime));
    gainRelease = Math.exp(-1.0/(sampleRate()*releaseTime));
    
    for(var i = 0 ; i < buffer.length ; i++){
      var envelopeIn = Math.abs(buffer[i]);
      if(envelopeOut < envelopeIn){
        envelopeOut = envelopeIn + gainAttack * (envelopeOut - envelopeIn);
      } else {
        envelopeOut = envelopeIn + gainRelease * (envelopeOut - envelopeIn);
      }
      result[i] = envelopeOut;
    }
    
    return result;
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
  background(0);
	console.clear();
}

var counter = 0;

function draw() {
	
  let bins = fft.analyze();
	
	var windowed = new Float32Array(bins.length);
	
  for (var i = 0; i < hWindow.length; i++) {
    windowed[i] = bins[i] * hWindow[i];    
  }
	
	var r8Max = zMax8(windowed);
	var r8MaxSum = 0;

	stroke(r8Max[8]);
	for (var k = 0; k < r8Max.length; k++) {
	  r8MaxSum += r8Max[k];
		stroke(55*Math.cos(r8MaxSum));
    line(counter, 0, counter, 20);
	}
	
	var t1 = r8MaxSum/19;

	// todo: scaler
	var er = e(fft.waveform()); //peak - ts -  = shred
	for(var j = 0; j < er.length; j++) {
		push();
	  stroke(255*er[j]);
		point(counter, 20+Math.pow(er[j],2)*55);
		pop();
	}
			
  push();
    var img = createImage(windowed.length, 1);
    img.loadPixels();
    for(var x = 0; x < img.width; x++) {
      for(var y = 0; y < img.height; y++) {
        var a = map(y, 0, img.height, 255, 0);
				if (windowed[x] > t1)
          img.set(x, y, [t1*Math.log(windowed[x]), 0, 0, a]); //log, tan
				else
					img.set(x, y, [0, 0, 0, 0]); 
      }
    }
    img.updatePixels();
    image(img, 0, 20+counter);
  pop();
	
	counter++;
	if (counter > width) {
		background(0);
		counter = 0;
	}
	
}
