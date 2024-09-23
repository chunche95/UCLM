require('dotenv').config();
const { MongoClient } = require('mongodb');
const { generateSensorData } = require('./sensor_simulator');

// Configuración de variables de entorno con los datos del archivo .env
const uri = process.env.MONGO_URI;
const dbName = process.env.DB_NAME;
const collectionName = process.env.COLLECTION_NAME;

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function demo() {
    for (let i = 0; i < 5; i++) {
        console.log(`Waiting ${i} seconds...`);
        await sleep(i * 1000);
    }
    console.log('Done');
}

// Conectar a la base de datos MongoDB Atlas
async function connectToMongoDB() {
    const client = new MongoClient(uri, { useNewUrlParser: true, useUnifiedTopology:true});
    try {
        await client.connect();
        console.log('Connected to MongoDB Atlas - Successfully connected');
        demo();
        const db = client.db(dbName);
        const collection = db.collection(collectionName);
        return { client, collection };
    } catch (error) {
        console.error('Error connecting to MongoDB Atlas - Error connecting', error);
        throw error;
    }
}

// Funciones CRUD

// CREATE 
async function insertSensorData(collection, data) {
    try {
        const result = await collection.insertMany(data);
        console.log('Data successfully inserted', result.insertedCount);        
    } catch (error) {
        console.error('Error inserting data - Error inserting', error);
    }
}

// READ 
async function getSensorData(collection) {
    try {
        const data = await collection.find().toArray();
        console.log('Data successfully retrieved - ', data);
    } catch (error) {
        console.error('Error getting data - Error', error);
    }
}

// UPDATE
async function updateSensorData(collection, sensorId, newValue) {
    try {
        const result = await collection.updateOne( 
            { sensorId: sensorId },
            { $set: {value: newValue} }
        );
        console.log('Data successfully updated - ', result.modifiedCount);
    } catch (error) {
        console.error('Error updating data - Error', error);
    }
}

// DELETE
async function deleteSensorData(collection, sensorId) {
    try {
        const result = await collection.deleteOne(
            {
                sensorId: sensorId
            }
        );
        console.log('Data successfully deleted', result.modifiedCount);
    } catch (error) {
        console.error('Error deleting data - Error', error);
    }
}

// Funcion principal
async function main() {
    const { client, collection } = await connectToMongoDB();

    // Simular datos de sensores
    const sensorData = generateSensorData(Math.random() * 100);

    // Operaciones CRUD
    await insertSensorData(collection, sensorData); // CREATE
    await getSensorData(collection); // READ
    await updateSensorData(collection, sensorData[0].sensorId, 99.9); // UPDATE
    await deleteSensorData(collection, sensorData[1].sensorId); // DELETE

    client.close(); // Cerrar conexión
}

main().catch(console.error);
