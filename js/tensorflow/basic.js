const tf = require('@tensorflow/tfjs')
require('@tensorflow/tfjs-node')

const model = tf.sequential();

const config_hidden = {
  inputShape:[3],
  activation:'sigmoid',
  units:4
}

const config_output={
  units:2,
  activation:'sigmoid'
}

const hidden = tf.layers.dense(config_hidden);
const output = tf.layers.dense(config_output);

model.add(hidden);
model.add(output);

const optimize=tf.train.sgd(0.1);

const config={
  optimizer:optimize,
  loss:'meanSquaredError'
}

model.compile(config);
console.log('Model Successfully Compiled');

const x_train = tf.tensor([
  [0.1,0.5,0.1],
  [0.9,0.3,0.4],
  [0.4,0.5,0.5],
  [0.7,0.1,0.9]
])

const y_train = tf.tensor([
  [0.2,0.8],
  [0.9,0.10],
  [0.4,0.6],
  [0.5,0.5]
])

const x_test = tf.tensor([
  [0.9,0.1,0.5]
])

train_data().then(function(){
  console.log('Training is Complete');
  console.log('Predictions :');
  model.predict(x_test).print();
})

async function train_data(){
  for(let i=0;i<10;i++){
  const res = await model.fit(x_train,y_train,epoch=1000,batch_size=10);
   console.log(res.history.loss[0]);
  }
}
