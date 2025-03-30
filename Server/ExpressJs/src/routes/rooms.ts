import { Router } from 'express';
import { prisma } from '../prisma';

const router = Router();

const UpperLimit = 100;

router.get('/', async (req, res) => {
  try {
      const page = parseInt(req.query.page as string) || 1;
      let limit = parseInt(req.query.limit as string) || UpperLimit;
      limit = Math.min(limit, UpperLimit);
      const skip = (page - 1) * limit;

      const rooms = await prisma.room.findMany({
          skip,
          take: limit,
      });

      res.json(rooms);
  } catch (error) {
      res.status(500).json({ error: "Internal Server Error" });
  }
});

export default router;
