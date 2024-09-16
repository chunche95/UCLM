function addToArray(data, array, callback) {
    if (!array) {
        callback(new Error('Invalid array passed'), null)
    } else {
        array.push(data)
        callback(null, array)
    }
}

var array = [1,2,3];
addToArray(4, array, function(err) {
    if (err) return console.error(err.message);
    console.log(array); // Output: [1, 2, 3, 4]    
})


