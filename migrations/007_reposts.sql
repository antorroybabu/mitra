CREATE TABLE IF NOT EXISTS reposts (
    post_id BIGINT NOT NULL REFERENCES posts(id) ON DELETE CASCADE,
    user_id BIGINT NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    created_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
    PRIMARY KEY (post_id, user_id)
);

CREATE INDEX IF NOT EXISTS idx_reposts_user_created ON reposts (user_id, created_at DESC);
CREATE INDEX IF NOT EXISTS idx_reposts_created ON reposts (created_at DESC, post_id);
