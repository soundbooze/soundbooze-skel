const fs = require('fs');
const path = require('path');

function listDirectory(dir) {

  fs.readdir(dir, function(err, items) {

    for (var i in items) {
      if (fs.statSync(dir + items[i]).isDirectory())
        console.log(items[i]);
    }

  });

}

function scanFiles(dir, ext) {

  var files = fs.readdirSync(dir);

  for (var i in files) {
    if (path.extname(files[i]) === ext) {
      console.log(files[i]);
    }
  }

}

var dir = process.argv[2];

if ((dir.substring(dir.length - 1)) !== '/') {
  dir += '/';
}

// listDirectory(dir);

scanFiles(dir, '.wav');
