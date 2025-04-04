import { Router } from 'express';
import { prisma } from '../prisma';

const router = Router();

const UpperLimit = 100;

router.get('/', async (req, res) => {
    try {
        const limit = Math.min(
            Number(req.query.limit) || UpperLimit,
            UpperLimit
        );
        const offset = Number(req.query.offset) || 0;

        const rooms = await prisma.$queryRaw<
            {
                id: string;
                name: string;
                type: string;
                description: string | null;
                avatar_url: string | null;
                created_at: Date;
                most_recent_timestamp: Date;
                last_message_id: string | null;
                last_message_content: string | null;
                last_message_created_at: Date | null;
                last_message_user_id: string | null;
                last_message_user_username: string | null;
                last_message_user_avatar_url: string | null;
                member_count: number;
            }[]
        >`
            SELECT r.id, r.name, r.type, r.description, r.avatar_url, r.created_at,
                COALESCE(
                    lm.created_at, 
                    r.created_at
                ) AS most_recent_timestamp,
                lm.id AS last_message_id,
                lm.content AS last_message_content,
                lm.created_at AS last_message_created_at,
                u.id AS last_message_user_id,
                u.username AS last_message_user_username,
                u.avatar_url AS last_message_user_avatar_url,
                COUNT(rm.user_id) AS member_count
            FROM 
                room r
            LEFT JOIN 
                message lm ON r.last_message_id = lm.id
            LEFT JOIN 
                "user" u ON lm.user_id = u.id
            LEFT JOIN 
                room_membership rm ON r.id = rm.room_id
            GROUP BY 
                r.id, lm.id, u.id
            ORDER BY 
                most_recent_timestamp DESC
            LIMIT ${limit} OFFSET ${offset};
        `;

        const formattedRooms = rooms.map((room) => ({
            id: room.id,
            name: room.name,
            type: room.type,
            description: room.description,
            avatar_url: room.avatar_url,
            created_at: room.created_at,
            last_message: room.last_message_id
                ? {
                      id: room.last_message_id,
                      content: room.last_message_content,
                      created_at: room.last_message_created_at,
                      user: {
                          id: room.last_message_user_id,
                          username: room.last_message_user_username,
                          avatar_url: room.last_message_user_avatar_url,
                      },
                  }
                : null,
            member_count: Number(room.member_count),
        }));

        res.json({
            data: formattedRooms,
            metadata: { limit, offset, total: rooms.length },
        });
    } catch (error) {
        console.error(error);
        res.status(500).json({
            error: { code: 500, message: 'Internal server error' },
        });
    }
});

router.get('/:id', async (req, res) => {
    const roomId = req.params.id;
    const userLimit = 20;
    const userOffset = 0;
    const messageLimit = 20;
    const messageOffset = 0;

    try {
        const room = await prisma.room.findUnique({
            where: { id: Number(roomId) },
            include: {
                room_membership: {
                    take: userLimit,
                    include: {
                        user: {
                            select: {
                                id: true,
                                username: true,
                                avatar_url: true,
                            },
                        },
                    },
                },
                message_message_room_idToroom: {
                    orderBy: { created_at: 'desc' },
                    take: messageLimit,
                    include: {
                        user: {
                            select: {
                                id: true,
                                username: true,
                                avatar_url: true,
                            },
                        },
                    },
                },
            },
        });

        if (!room) {
            res.status(404).json({
                error: { code: 404, message: 'Room not found' },
            });
            return;
        }

        res.json({
            id: room.id,
            name: room.name,
            type: room.type,
            description: room.description,
            avatar_url: room.avatar_url,
            created_at: room.created_at,
            members: {
                data: room.room_membership.map((membership) => ({
                    id: membership.user.id,
                    username: membership.user.username,
                    avatar_url: membership.user.avatar_url,
                })),
                metadata: {
                    total: room.room_membership.length,
                    limit: 20,
                    offset: 0,
                    next: total > limit ? `/rooms/${roomId}?limit=${limit}&offset=${offset + limit}` : null,
                },
            },
            messages: room.message_message_room_idToroom.map((message) => ({
                id: message.id,
                content: message.content,
                created_at: message.created_at,
                user: {
                    id: message.user.id,
                    username: message.user.username,
                    avatar_url: message.user.avatar_url,
                },
            })),
        });
    } catch (error) {
        console.error(error);
        res.status(500).json({
            error: { code: 500, message: 'Internal server error' },
        });
    }
});

export default router;
