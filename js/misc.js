
 // one liners

  Math.min(...arr);
  Math.max(...arr);

  sum = arr.reduce((previous, current) => current += previous);
  var ssum = arr1.reduce(function(a, b){return a+b;});

  // concat

  var arr1 = [1, 2, 3];
  var arr2 = [...arr1];
  arr2.push(4);

  arr1 = [0, 1, 2];
  arr2 = [3, 4, 5];
  arr1 = [...arr1, ...arr2];
  console.log(arr1);

  // occurence sum

  const a = [5, 5, 5, 2, 2, 5, 2, 2, 2, 9, 4];

  const aCount = new Map([...new Set(a)].map(
    x => [x, a.filter(y => y === x).length]
  ));

  console.log(aCount.get(5));

  // unique

  let arr = [1, 2, 1, 2, 3, 5, 4, 5, 3, 4, 4, 4, 4];
  let result = arr.sort().reduce((accumulator, current) => {
      const length = accumulator.length
      if (length === 0 || accumulator[length - 1] !== current) {
          accumulator.push(current);
      }
      return accumulator;
  }, []);

  // swap

  [a, b] = [b, a];

  // for

  let iterable = [10, 20, 30];
  for (let value of iterable) {
    value += 1;
  }

  // Map , iterable

  let items = [ ['foo', 3], ['bar', 9] ];
    items.forEach(([word, count]) => console.log(word+' '+count));

  let iterable = new Map([['a', 1], ['b', 2], ['c', 3]]);

  for (let [key, value] of iterable) {
    console.log(key, value);
  }

  // array scalar

  const myArray = [2, 3, 4, 5];
  const myArrayTimesTwo = myArray.map((value, index, array) => {
    return value * 2;
  });

  console.log(myArrayTimesTwo);

  // reduce

  var a = [0, 1, 2, 3, 4]

  var c = a.reduce(function(accumulator, currentValue, currentIndex, array) {
    return accumulator + currentValue;
  });

  console.log(c);

  // group by

  var people = [
    { name: 'Alice', age: 21 },
    { name: 'Max',   age: 20 },
    { name: 'Jane',  age: 20 }
  ];

  function groupBy(objectArray, property) {
    return objectArray.reduce(function (acc, obj) {
      var key = obj[property];
      if (!acc[key]) {
        acc[key] = [];
      }
      acc[key].push(obj);
      return acc;
    }, {});
  }

  var groupedPeople = groupBy(people, 'age');

  console.log(groupedPeople);

  // object

  var people = [
    {
      name: "Mike Smith",
      family: {
        mother: "Jane Smith",
        father: "Harry Smith",
        sister: "Samantha Smith"
      },
      age: 35
    },
    {
      name: "Tom Jones",
      family: {
        mother: "Norah Jones",
        father: "Richard Jones",
        brother: "Howard Jones"
      },
      age: 25
    }
  ];

  for (var {name: n, family: { father: f } } of people) {
    console.log("Name: " + n + ", Father: " + f);
  }

  // group count max

  let arr = [9, 2, 1, 2, 3, 5, 4, 5, 3, 4, 4, 4, 4];

  let unique = arr.sort().reduce((accumulator, current) => {
      const length = accumulator.length
      if (length === 0 || accumulator[length - 1] !== current) {
          accumulator.push(current);
      }
      return accumulator;
  }, []);

  const aCount = new Map([...new Set(arr)].map(
    x => [x, arr.filter(y => y === x).length]
  ));

  var hist = [];
  unique.forEach(function(item){
    hist.push({item: item, total: aCount.get(item)});
  });

  console.log(hist);
