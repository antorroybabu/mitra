CREATE TABLE IF NOT EXISTS recommendation_events (
    event_id BIGINT PRIMARY KEY,
    user_id BIGINT NOT NULL,
    content_id BIGINT NOT NULL,
    creator_id BIGINT NOT NULL DEFAULT 0,
    event_type SMALLINT NOT NULL,
    occurred_at TIMESTAMPTZ NOT NULL,
    received_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
    metadata JSONB NOT NULL DEFAULT '{}'::jsonb,
    CHECK (event_id > 0),
    CHECK (user_id > 0),
    CHECK (content_id > 0)
);

CREATE INDEX IF NOT EXISTS idx_recommendation_events_user_time
    ON recommendation_events (user_id, occurred_at DESC, event_id DESC);

CREATE INDEX IF NOT EXISTS idx_recommendation_events_content_time
    ON recommendation_events (content_id, occurred_at DESC);

CREATE INDEX IF NOT EXISTS idx_recommendation_events_creator_time
    ON recommendation_events (creator_id, occurred_at DESC);

CREATE INDEX IF NOT EXISTS idx_recommendation_events_type_time
    ON recommendation_events (event_type, occurred_at DESC);
