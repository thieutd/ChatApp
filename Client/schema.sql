CREATE TABLE IF NOT EXISTS user (
    id INTEGER PRIMARY KEY,
    username TEXT NOT NULL,
    role TEXT,
    avatar_url TEXT,
    created_at TEXT,
    is_deleted INTEGER,
    last_synced TEXT DEFAULT (datetime('now'))
);

CREATE TABLE IF NOT EXISTS room (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    type TEXT,
    description TEXT,
    avatar_url TEXT,
    created_at TEXT,
    is_deleted INTEGER,
    last_message_id INTEGER,
    last_synced TEXT DEFAULT (datetime('now'))
);

CREATE TABLE IF NOT EXISTS room_membership (
    user_id INTEGER NOT NULL,
    room_id INTEGER NOT NULL,
    role TEXT,
    created_at TEXT,
    is_deleted INTEGER,
    last_synced TEXT DEFAULT (datetime('now')),
    PRIMARY KEY (user_id, room_id),
    FOREIGN KEY (user_id) REFERENCES user(id),
    FOREIGN KEY (room_id) REFERENCES room(id)
);

CREATE TABLE IF NOT EXISTS message (
    id INTEGER PRIMARY KEY,
    user_id INTEGER NOT NULL,
    room_id INTEGER NOT NULL,
    content TEXT,
    created_at TEXT,
    is_deleted INTEGER,
    is_sent INTEGER,
    pending_id TEXT,
    last_synced TEXT DEFAULT (datetime('now')),
    FOREIGN KEY (user_id) REFERENCES user(id),
    FOREIGN KEY (room_id) REFERENCES room(id)
);

-- CREATE INDEX idx_user_username ON user(username);
-- CREATE INDEX idx_room_name ON room(name);
CREATE INDEX idx_message_room ON message(room_id, created_at);
-- CREATE INDEX idx_message_user ON message(user_id);
CREATE INDEX idx_room_membership_user ON room_membership(user_id);
CREATE INDEX idx_message_pending ON message(pending_id) WHERE pending_id IS NOT NULL;
-- CREATE INDEX idx_active_rooms ON room(id) WHERE is_deleted = 0;
-- CREATE INDEX idx_room_last_message ON room(last_message_id);

-- CREATE VIEW v_rooms_with_messages AS
-- SELECT 
--     r.id AS room_id,
--     r.name AS room_name,
--     r.type AS room_type,
--     r.avatar_url AS room_avatar,
--     m.id AS last_message_id,
--     m.content AS last_message_content,
--     m.created_at AS last_message_date,
--     m.user_id AS last_message_user_id,
--     u.username AS last_message_username
-- FROM room r
-- LEFT JOIN message m ON r.last_message_id = m.id
-- LEFT JOIN user u ON m.user_id = u.id
-- WHERE r.is_deleted = 0;