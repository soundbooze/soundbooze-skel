const tf = require('@tensorflow/tfjs')

const a = tf.tensor1d([1, 2, 3]);
const b = tf.tensor1d([2, 2, 2]);

a.equal(b).print();
