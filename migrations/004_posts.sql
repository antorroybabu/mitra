CREATE TABLE IF NOT EXISTS posts (
    id BIGSERIAL PRIMARY KEY,
    author_id BIGINT NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    body TEXT NOT NULL,
    created_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
    updated_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
    deleted_at TIMESTAMPTZ,
    CONSTRAINT posts_body_length CHECK (char_length(body) BETWEEN 1 AND 5000)
);

CREATE INDEX IF NOT EXISTS idx_posts_author_created ON posts (author_id, created_at DESC, id DESC);
CREATE INDEX IF NOT EXISTS idx_posts_created ON posts (created_at DESC, id DESC);
