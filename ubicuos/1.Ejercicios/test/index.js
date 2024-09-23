require('dotenv').config();
const { MongoClient, Timestamp } = require('mongodb');
const uri = process.env.MONGO_URI;
const dbName = process.env.DB_NAME;

async function connectToMOngo() {
    const client = new MongoClient(uri);
    await client.connect();
    console.log("Conectado a Mongo");
    return client.db(dbName);
}

// Función para generar datos simulados de sensores IoT
function generateSensorData() {
    const sensorTypes = ['Temperatura', 'Humedad', 'Acelerómetro', 'Sensor PIR', 'Ubicación', 'Optimo', 'Agua', 'Imagen', 'Presión', 'Movimiento'];
    const sensorData = {
        sensorId: `sensor-${Math.floor(Math.random() * 1000)}`, // ID del sensor
        type: sensorTypes[Math.random(Math.random() * sensorTypes.length)],
        value: Math.random() * 100, // Valor simulado (ajusta según el tipo de sensor)
        timestamp: new Date() // Timestamp del sensor actual 
    };
    return sensorData;
}


// Función para insertar múltiples datos del sensor
async function insertSensorData(db, count) {
    const collection = db.collection('sensor_data');
    const sensorDataArray = [];

    for (let i = 0; i < count; i++) {
        const sensorData = generateSensorData();
        sensorDataArray.push(sensorData);
    }

    try {
        const result = await collection.insertMany(sensorDataArray);
        console.log(`${result.insertedCOunt} datos insertados`);
    } catch (err) {
        console.error("Error al insertar datos del sensor: " + err.message);
    }
}

// Función para leer datos de sensores
async function readSensorData(db) {
    const collection = db.collection('sensor_data');
    const data = await collection.find().toArray();
    console.log("Datos de sensores: " + JSON.stringify(data));
}

// Función para actualizar un dato de sensor
async function updateSensorData(db, sensorId, newValue) {
    const collection = db.collection('sensor_data');
    const result = await collection.updateOne(
        {
            sensorId: sensorId
        }, 
        {
            $set: 
            {
                value: newValue
            }
        }
    );
    console.log('Datos actualizados: ${result.modifiedCount}');    
}

// Función para eliminar un dato de sensor
async function deleteSensorData(db, sensorId) {
    const collection = db.collection('sensor_data');
    const result = await collection.deleteOne(
        {
            sensorId: sensorId 
        }
    );
    console.log('Datos eliminados: ${result.deletedCount}');
}


// Función principal
async function main() {
    const db = await connectToMOngo();
    // Insertar 1000 datos de sensores 
    await insertSensorData(db, 1000);
    // Leer todos los datos de sensores
    await readSensorData(db);
    // Actualizar un dato de sensor  - Ejemplo
    await updateSensorData(db, 'sensor-1', 75.5);
    // Eliminar un dato de sensor - Ejemplo
    await deleteSensorData(db, 'sensor-1'); 
    // Cerrar conexión
    //db.client.close();
    process.exit();
}

main().catch(console.error);