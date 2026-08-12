CREATE TABLE IF NOT EXISTS users (
 id BIGINT PRIMARY KEY,
 username VARCHAR(64) NOT NULL UNIQUE,
 display_name VARCHAR(120) NOT NULL,
 created_at TIMESTAMPTZ NOT NULL DEFAULT NOW()
);
CREATE TABLE IF NOT EXISTS posts (
 id BIGINT PRIMARY KEY,
 author_id BIGINT NOT NULL REFERENCES users(id),
 body TEXT NOT NULL,
 created_at TIMESTAMPTZ NOT NULL DEFAULT NOW()
);
CREATE INDEX IF NOT EXISTS idx_posts_author_created ON posts(author_id, created_at DESC, id DESC);
CREATE TABLE IF NOT EXISTS follows (
 follower_id BIGINT NOT NULL REFERENCES users(id),
 following_id BIGINT NOT NULL REFERENCES users(id),
 created_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
 PRIMARY KEY(follower_id, following_id),
 CHECK(follower_id <> following_id)
);
CREATE INDEX IF NOT EXISTS idx_follows_following ON follows(following_id, follower_id);
CREATE TABLE IF NOT EXISTS post_likes (
 user_id BIGINT NOT NULL REFERENCES users(id),
 post_id BIGINT NOT NULL REFERENCES posts(id),
 created_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
 PRIMARY KEY(user_id, post_id)
);
CREATE INDEX IF NOT EXISTS idx_post_likes_post ON post_likes(post_id, created_at DESC);
CREATE TABLE IF NOT EXISTS comments (
 id BIGINT PRIMARY KEY,
 user_id BIGINT NOT NULL REFERENCES users(id),
 post_id BIGINT NOT NULL REFERENCES posts(id),
 body TEXT NOT NULL,
 created_at TIMESTAMPTZ NOT NULL DEFAULT NOW()
);
CREATE INDEX IF NOT EXISTS idx_comments_post_created ON comments(post_id, created_at DESC, id DESC);
