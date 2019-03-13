// https://github.com/mfcc64/html5-showcqtbar
// - simplified SO MUDAH DIMENGERTI -log day1

function start_showcqtbar(width, height, bar_h, stream) {
    var audio_ctx = new(window.AudioContext || window.webkitAudioContext)();
    function resume_audio_ctx() {
        if (audio_ctx.state === "suspended") {
            audio_ctx.resume();
            window.setTimeout(resume_audio_ctx, 100);
        }
    }
    resume_audio_ctx();
    var analyser_l = audio_ctx.createAnalyser();
    var analyser_r = audio_ctx.createAnalyser();
    var splitter = audio_ctx.createChannelSplitter(2);
    var source = stream ?
        audio_ctx.createMediaStreamSource(stream) :
        audio_ctx.createMediaElementSource(document.getElementById("my-audio"));

    var canvas = document.getElementById("my-canvas").getContext("2d", {alpha:true});
    var bar_knob_value = 19;
    var brightness_knob_value = 25;
    var showcqtbar = new ShowCQTBar(audio_ctx.sampleRate, width, bar_h,
                                    Math.pow(10, bar_knob_value/20),
                                    Math.pow(10, brightness_knob_value/20), 1);

    analyser_l.fftSize = showcqtbar.fft_size;
    analyser_r.fftSize = showcqtbar.fft_size;
    source.connect(splitter);
    splitter.connect(analyser_l, 0);
    splitter.connect(analyser_r, 1);
    if (!stream)
        splitter.connect(audio_ctx.destination);
    var audio_data_l = showcqtbar.get_input_array(0);
    var audio_data_r = showcqtbar.get_input_array(1);
    var line_buffer_tmp = null, line_buffer = null;
    var line_buffer = showcqtbar.get_output_array();
    var img_buffer = canvas.createImageData(width, height);

    function draw() {
        requestAnimationFrame(draw);
        analyser_l.getFloatTimeDomainData(audio_data_l);
        analyser_r.getFloatTimeDomainData(audio_data_r);
        showcqtbar.calc();
        var waterfall = 0;

        for (var y = 0; y < height/2; y++) {
            showcqtbar.render_line(y);
            img_buffer.data.set(line_buffer, 4*width*y); // #1
            if (!waterfall || y >= bar_h) {
                img_buffer.data.set(line_buffer, 4*width*(height-1-y)); // #2
            }
        }

        if (img_buffer.data.copyWithin) {
            img_buffer.data.copyWithin(4*width*(height-bar_h+waterfall), 4*width*(height-bar_h), 4*width*(height-waterfall)); // #3
        } else {
            for (var y = 0; y < bar_h - waterfall; y++) {
                var dst = 4 * width * (height - y - 1);
                var src = 4 * width * (height - y - 1 - waterfall);
                for (var x = 0; x < 4*width; x++)
                    img_buffer.data[dst+x] = img_buffer.data[src+x]; // #4
            }
        }
        var src0 = 4 * width * (height - bar_h - 1);
        var src1 = 4 * width * (height - bar_h + waterfall);
        var dst = 4 * width * (height - bar_h);
        for (var x = 0; x < 4*width; x++)
            img_buffer.data[dst+x] = img_buffer.data[src0+x]; // #5
        for (var y = 1; y < waterfall; y++) {
            var dst = 4 * width * (height - bar_h + y);
            var a1 = y / waterfall;
            var a0 = 1.0 - a1;
            for (var x = 0; x < 4*width; x++) {
                img_buffer.data[dst+x] = (a0 * img_buffer.data[src0+x] + a1 * img_buffer.data[src1+x] + 0.5)|0; // #6
            }
        }

        for (var i = 0; i < img_buffer.data.length; i += 4) {
          img_buffer.data[i + 0] = img_buffer.data[i + 0] - 80;
          img_buffer.data[i + 1] = img_buffer.data[i + 1] - 19;
          img_buffer.data[i + 2] = img_buffer.data[i + 2] - 10;
          img_buffer.data[i + 3] = img_buffer.data[i + 3];
        }

        canvas.putImageData(img_buffer, 0, 0);

    }
    requestAnimationFrame(draw);
}

function resize_canvas(w, h, bar_h, axis_h) {
    document.getElementById("my-canvas").width = w;
    document.getElementById("my-canvas").height = h;
    document.getElementById("my-div-canvas").style.height = h + "px";
    document.getElementById("my-div-img").style.top = bar_h + "px";
    document.getElementById("my-img").width = w;
    document.getElementById("my-img").height = axis_h;
    if (document.getElementById("my-audio"))
        document.getElementById("my-audio").style.width = w + "px";
}

window.addEventListener("load", function(event) {
    var w = 0, h = 0, axis_h = 0, bar_h = 0;
    var auto_size = 0;

    w = Math.min(Math.max(Math.floor(window.innerWidth), 640), 1920);
    h = window.innerHeight;

    var expected_h = Math.floor((window.innerHeight - document.getElementById("my-audio-div").clientHeight
                                - document.getElementById("my-input-div").clientHeight
                                - document.getElementById("my-p").clientHeight)/2) * 2;
    h = Math.min(h, Math.max(expected_h, 120));

    axis_h = Math.round(w / 80) * 2;
    bar_h = ((h - axis_h)/2)|0;

    resize_canvas(w, h, bar_h, axis_h);

    if (document.getElementById("my-audio")) {
        start_showcqtbar(w, h, bar_h, null);
    } else if (navigator.mediaDevices) {
        navigator.mediaDevices.getUserMedia({audio: true, video: false})
        .then(function(stream) {
            start_showcqtbar(w, h, bar_h, stream);
        })
        .catch(function(err) {
            alert("Error on navigator.mediaDevices.getUserMedia(): " + err.name + ".");
        });
    } else {
        alert("navigator.mediaDevices is not supported on your browser.");
    }
});
