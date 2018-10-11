const tf = require('@tensorflow/tfjs')

const a = tf.tensor1d([false, false, true, true], 'bool');
const b = tf.tensor1d([false, true, false, true], 'bool');

a.logicalAnd(b).print();
a.logicalOr(b).print();
a.logicalXor(b).print();
a.logicalNot().print();
a.notEqual(b).print();

const cond = tf.tensor1d([false, false, true], 'bool');
const aa = tf.tensor1d([1 , 2, 3]);
const bb = tf.tensor1d([-1, -2, -3]);

aa.where(cond, bb).print();
