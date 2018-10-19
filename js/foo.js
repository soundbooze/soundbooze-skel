var FooGL = {

  globalFoo : 51,

  isFoo: function () {
    console.log(true);
  },

  getFoo: function () {
    console.log(this.globalFoo);
  }

};

// FooGL.isFoo();
// console.log(FooGL.globalFoo);
