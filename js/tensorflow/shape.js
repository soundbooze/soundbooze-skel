const tf = require('@tensorflow/tfjs')

const x = tf.tensor1d([1, 2, 3, 4]);
x.reshape([2, 2]).print();

const y = tf.tensor([1, 2, 3, 4], [1, 1, 4]);
y.squeeze().print();
