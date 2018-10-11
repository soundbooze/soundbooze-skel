const tf = require('@tensorflow/tfjs')

const x = tf.tensor([1, 2, 3, 4]);
x.cumsum().print();

const y = tf.tensor([[1, 2], [3, 4]]);
y.cumsum().print();

const z = tf.tensor1d([1, 2, 3, 4]);
const segmentIds = tf.tensor1d([1, 2, 0, 1], 'int32');
const numSegments = 3;

z.unsortedSegmentSum(segmentIds, numSegments).print()
