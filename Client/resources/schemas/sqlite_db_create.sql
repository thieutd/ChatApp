BEGIN TRANSACTION;
PRAGMA foreign_keys = OFF;
CREATE TABLE IF NOT EXISTS message (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, content TEXT, created_at TEXT, is_deleted INTEGER, is_sent INTEGER, pending_id TEXT, last_synced TEXT, user_id INTEGER, room_id INTEGER);
CREATE TABLE IF NOT EXISTS room (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name TEXT, type TEXT, description TEXT, avatar_url TEXT, created_at TEXT, is_deleted INTEGER, last_message_id INTEGER, last_synced TEXT);
CREATE TABLE IF NOT EXISTS room_membership (user_id INTEGER NOT NULL, room_id INTEGER NOT NULL, role TEXT, created_at TEXT, is_deleted INTEGER, last_synced TEXT, PRIMARY KEY (user_id, room_id));
CREATE TABLE IF NOT EXISTS user (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, username TEXT, role TEXT, avatar_url TEXT, created_at TEXT, is_deleted INTEGER, last_synced TEXT);
END TRANSACTION;
