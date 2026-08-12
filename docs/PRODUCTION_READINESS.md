# MITRA production completion gates

Creator: Antor Roy

The project is only considered production-complete when every gate below is implemented and verified; interfaces alone do not count.

- Build: clean C++20/CMake build with warnings treated as errors where practical.
- Tests: unit, integration, API, database, fuzz and load tests pass.
- Data: PostgreSQL migrations, constraints, indexes, transactions and backups are verified.
- Cache: Redis adapters, TTLs, invalidation and failure behavior are verified.
- Auth: Argon2id password hashing, secure sessions, rotation, revocation, CSRF policy where applicable and authorization are verified.
- API: Drogon controllers, schema validation, request limits, error contracts and rate limiting are verified.
- Media: authenticated uploads, type/size limits, object storage, transcoding isolation and malware/content scanning policy are verified.
- Realtime: authenticated WebSocket and WebRTC signaling with abuse limits is verified.
- Recommendation: event ingestion, candidate retrieval, ranking, diversity, safety and cursor feeds are verified with offline and online evaluation.
- Search: indexed queries, pagination, authorization filtering and abuse controls are verified.
- ROY: ledger, wallet, transaction validation, replay protection, consensus/P2P and RPC require implementation plus independent security review before any real-value deployment.
- Post-quantum security: use standardized, reviewed PQC algorithms and crypto-agile key/versioning; never claim absolute quantum-proof security.
- Operations: secrets management, TLS, least privilege, structured logs, metrics, tracing, alerts, backups and disaster recovery are verified.
- Deployment: reproducible Docker builds, CI/CD, migrations and rollback procedures are verified.

This document is a gate, not a claim that all gates are currently complete.
