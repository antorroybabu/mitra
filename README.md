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

See `docs/architecture/overview.md` for the complete architecture and `docs/security/security-model.md` for security requirements.

## Development principle

Start as a modular system with clear service boundaries. Extract independently scalable services when measurement justifies it. Correctness, security, observability, and testability take priority over premature optimization.

## Phase 1

The initial repository establishes the structure, CMake, configuration, Docker development environment, health/readiness endpoints, CI, and security baseline. No secrets belong in Git.
