gaussianNoise = function (variance) {
  var rand1 = Math.random();
  rand1 = -2 * Math.log(rand1);

  var rand2 = Math.random();
  rand2 = 2 * Math.PI * rand2;

  var spare = Math.sqrt(rand1 * variance) * Math.sin(rand2);
  return Math.sqrt(rand1 * variance) * Math.cos(rand2);
}
