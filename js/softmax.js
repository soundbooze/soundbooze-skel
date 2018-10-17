function softmax(x) {
  var max = 0.0;
  var sum = 0.0;

  for (var i=0; i < x.length; i++) 
    if (max < x[i]) 
      max = x[i];

  for (var i=0; i < x.length; i++) {
    x[i] = Math.exp(x[i] - max);
    sum += x[i];
  }

  for (var i=0; i < x.length; i++) 
    x[i] /= sum;

  return x;
}
