
  var v1 = ARRAY.sort(function(a, b){return a-b}).reduce((accumulator, current) => {
    const length = accumulator.length
    if (length === 0 || accumulator[length - 1] !== current) {
      accumulator.push(current);
    }
    return accumulator;
  }, []);

  var min1 = v1[0];
  var max1 = v1[v1.length - 1];
  
  var zV1 = [];

  for (var i = 0; i < v1.length; i++) {
    zV1.push((v1[i] - min1) / (max1 - min1));
    console.log(zV1[i]);
  }
