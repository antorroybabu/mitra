CREATE TABLE IF NOT EXISTS behavior_events (
    event_id UUID PRIMARY KEY,
    user_id BIGINT NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    content_id BIGINT NOT NULL,
    event_type SMALLINT NOT NULL,
    occurred_at TIMESTAMPTZ NOT NULL,
    schema_version INTEGER NOT NULL DEFAULT 1,
    received_at TIMESTAMPTZ NOT NULL DEFAULT NOW()
);

CREATE INDEX IF NOT EXISTS idx_behavior_user_time ON behavior_events (user_id, occurred_at DESC, event_id DESC);
CREATE INDEX IF NOT EXISTS idx_behavior_content_time ON behavior_events (content_id, occurred_at DESC, event_id DESC);
