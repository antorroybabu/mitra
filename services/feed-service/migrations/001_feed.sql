CREATE TABLE IF NOT EXISTS feed_events (
 user_id BIGINT NOT NULL REFERENCES users(id) ON DELETE CASCADE,
 post_id BIGINT NOT NULL REFERENCES posts(id) ON DELETE CASCADE,
 event_type SMALLINT NOT NULL,
 created_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
 PRIMARY KEY(user_id, post_id, event_type)
);
CREATE INDEX IF NOT EXISTS idx_feed_events_user_created ON feed_events(user_id, created_at DESC, post_id DESC);
