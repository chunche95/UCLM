function addToArray(data, array) {
    setTimeout(function () {
        array.push(data);
    }, 1000);
    
}

var array = [1,2,3];
addToArray(4, array);
console.log(array); // Output: [1, 2, 3, 4]    


