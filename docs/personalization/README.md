# Personalization & Recommendation Platform

MITRA includes a dedicated personalization platform for relevant, user-controlled content discovery. It is a first-class subsystem, not a feed-only feature.

## Goals

- Learn changing user interests from explicit and implicit signals.
- Personalize home, following, explore, and short-video feeds.
- Combine candidate generation, ranking, diversity, freshness, quality, and safety.
- Support long-term relevance without manipulative dark patterns.
- Give users direct controls such as Not Interested, mute topic, and mute creator.
- Minimize collected behavioral data and enforce retention/access policies.
- Prevent fake engagement, bot activity, and coordinated recommendation manipulation.

## Architecture

```text
User actions
  |
  v
Behavior Event Collector
  |
  +--> privacy / consent / minimization
  |
  v
Kafka / Redpanda
  |
  +--> Behavior Service ----> User Interest Model
  |
  +--> Content Feature Pipeline
  |
  +--> Anti-Abuse Signals
  |
  v
Recommendation Service
  |
  +--> Candidate Generation
  |      - following
  |      - interest similarity
  |      - collaborative signals
  |      - fresh content
  |      - trending
  |
  +--> Ranking
  |      - relevance
  |      - recency
  |      - watch time
  |      - quality
  |      - relationship
  |      - negative signals
  |
  +--> Diversity / Exploration
  |
  +--> Safety / Moderation / Eligibility
  |
  v
Feed Service --> Redis --> Client
```

## Behavioral signals

### Explicit

- Follow/unfollow
- Like/dislike
- Bookmark
- Search
- Topic/hashtag follow
- Not Interested
- Hide creator/topic
- Report

### Implicit

- Impression
- Click
- Dwell/watch time
- Video completion percentage
- Skip
- Rewatch
- Share
- Comment
- Profile visit

Do not treat a single action as a permanent statement of identity or preference. Interest scores are dynamic and time-decayed.

## Interest model

The system maintains evolving topic/content affinity rather than a fixed personality profile. Recent behavior receives greater weight than stale behavior. Users can inspect and influence recommendation controls.

## Ranking safety

Recommendation ranking must not be based only on raw likes or engagement. Use trusted engagement, unique-user quality, watch behavior, account quality, spam/abuse signals, and content eligibility. Apply safety and moderation filters before delivery.

## Anti-manipulation

Protect ranking against bots, Sybil accounts, coordinated engagement, spam, and artificial watch/like inflation. Keep anti-abuse signals separate from user-facing behavioral profiles where possible.

## Privacy and security

- Collect only signals necessary for defined recommendation purposes.
- Encrypt sensitive data in transit and at rest.
- Enforce service-to-service authorization.
- Restrict access to behavioral data by least privilege.
- Maintain auditable access logs for sensitive data.
- Define retention/deletion policies.
- Never expose raw behavioral histories to clients unless explicitly designed and authorized.
- Never use behavioral data as a substitute for authentication or authorization.

## Initial implementation

Start with deterministic/rule-based scoring and clean interfaces for future ML ranking. Do not fabricate AI/ML capabilities or claim model performance without measurements.

Recommended service boundaries:

- `services/behavior-service`
- `services/recommendation-service`
- `services/feed-service`
- `services/anti-abuse-service`
- `services/moderation-service`
