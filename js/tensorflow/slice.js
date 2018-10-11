const tf = require('@tensorflow/tfjs')

const x = tf.tensor1d([1, 2, 3, 4]);
const indices = tf.tensor1d([1, 3, 3], 'int32');

x.gather(indices).print();

const y = tf.tensor2d([1, 2, 3, 4], [2, 2]);
const indicesy = tf.tensor1d([1, 1, 0], 'int32');

y.gather(indicesy).print();
