import express from 'express';
import dotenv from 'dotenv';
import apiKeyVerifier from './middlewares/apiKeyVerifier';
import roomsRouter from './routes/rooms';

dotenv.config();

const app = express();
const router = express.Router();

app.use(express.json());

if (process.env.NODE_ENV !== 'development') {
    app.use(apiKeyVerifier);
    console.log('API key middleware enabled');
}

router.use('/rooms', roomsRouter);
app.use(router);

const PORT = process.env.PORT || 3000;

app.listen(PORT, () => {
    console.log(`🚀 Server running on http://localhost:${PORT}`);
});
