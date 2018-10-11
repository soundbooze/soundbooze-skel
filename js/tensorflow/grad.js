const tf = require('@tensorflow/tfjs')

const f = x => x.pow(tf.scalar(3, 'int32'));
const g = tf.grad(f);
const gg = tf.grad(g);
const x = tf.tensor1d([2, 3]);
gg(x).print();
