# MITRA

High-performance, security-first social platform combining social feeds, media, realtime messaging, calls, personalization, creator economy, and an independent native-coin blockchain.

## Core stack

- C++20 + Drogon for backend services
- PostgreSQL for durable relational data
- Redis for cache, presence, rate limiting, and hot state
- Redpanda/Kafka for event streaming
- S3-compatible object storage + FFmpeg for media
- OpenSearch for search
- WebRTC for audio/video calls
- Next.js/React for web
- React Native for mobile
- Independent C++ blockchain core with a native coin
- Post-quantum-ready cryptographic agility; no custom cryptographic primitives

## Repository layout

See `docs/architecture/overview.md`, `docs/architecture/advanced-algorithms-data-structures.md`, and `docs/security/security-model.md` for the architecture contracts.

## Development principle

Start as a modular system with clear service boundaries. Extract independently scalable services when measurement justifies it. Correctness, security, observability, and testability take priority over premature optimization.

## Current implementation

Phase 1 is under active implementation on `feat/phase1-foundation`.

The branch contains the C++20/Drogon gateway foundation, health/readiness endpoints, CMake build structure, configuration template, and service boundaries. Database, cache, authentication, social APIs, personalization, realtime, media, and blockchain implementations are subsequent milestones and are not represented as complete merely by their directories.

No secrets belong in Git.
