# MITRA Architecture

## Product layers

1. Social: profiles, follows, posts, comments, reposts, stories, reels.
2. Realtime: direct messages, groups, channels, presence, WebSocket delivery.
3. Media: presigned uploads, object storage, FFmpeg workers, HLS, CDN.
4. Personalization: behavior events, interests, candidate generation, ranking, diversity, safety.
5. Trust & safety: moderation, anti-abuse, rate limits, audit logs, privacy controls.
6. Blockchain: independent native-coin network, wallet, P2P, mempool, consensus, RPC, explorer.

## Backend

C++20/Drogon services use Controller -> Service -> Repository boundaries. PostgreSQL is the durable source of truth; Redis is for hot state/cache; Redpanda/Kafka carries asynchronous domain events.

## Scalability

Use cursor pagination, connection pools, asynchronous I/O, event-driven workers, CDN delivery, feed caching, and measured horizontal scaling. Start modular; split services only when load or ownership boundaries justify it.

## Blockchain

The native coin is independent of TON. The chain must use well-studied consensus and cryptographic implementations, post-quantum-ready crypto agility, key rotation, secure wallet architecture, authenticated P2P, replay protection, and deterministic state transitions. Never invent cryptographic primitives.
