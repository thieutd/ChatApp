import express from 'express';

const apiKeyVerifier = (
    req: express.Request,
    res: express.Response,
    next: express.NextFunction
) => {
    const apiKey = req.headers['x-api-key'] as string;
    if (apiKey !== process.env.API_KEY) {
        res.status(403).json({ code: 403, message: 'Forbidden' });
    } else {
        next();
    }
};

export default apiKeyVerifier;
