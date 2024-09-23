// Simular datos  de sensores IoT
/* function generateSensorData(count) {  
  const sensorData = {
    temperature: (Math.random() * 30 + 10 * Math.random()).toFlixed(2),
    humidity: Math.random() * 100,
    light: Math.random() * 100,
    motion: Math.random() < 0.5
  };
    
  return sensorData;
}
*/

function generateSensorData (count) {
  const sensorTypes = [ 'temperature' , ' humidity' , ' light' , 'motion' ];
  const sensorData = [];

  for ( let i = 0; i < count; i++ ) {
    const sId = `sensor_${i+1}`;
    const sensorType = sensorTypes[Math.floor(Math.random() * sensorTypes.length)];
    const value = ( sensorType === 'temperature')
    ? (Math.random() * (40 - 10) - 30).toFixed(2) 
    : (Math.random() * 100).toFixed(2);

    sensorData.push( 
      {
        sId, 
        sensorType,
        value: parseFloat(value),
        timestamp: new Date().toISOString  // Simular timestamp
      }
    );
  }
  return sensorData;
}

module.exports = { generateSensorData };