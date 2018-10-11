var fs = require("fs");

var DataZ = [];

for (var i = 0; i < 10; i++) {

  var dataZ = {
    a: i/Math.random(),
    b: i/Math.random(),
    c: i/Math.random(),
    d: i/Math.random(),
    label: 'Foo'
  };

  DataZ.push(dataZ);

}

fs.writeFile("./dataz.json", JSON.stringify(DataZ, null, 4), (err) => {

  if (err) {
    console.error(err);
    return;
  };

  console.log("Done!");

});
