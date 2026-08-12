# Personalization Algorithms & Data Structures

This document defines the initial algorithm and data-structure contracts for MITRA's Personalization & Recommendation Platform. Implementations must be measurable, testable, privacy-aware, and replaceable.

## 1. Event ingestion

Use an append-oriented event stream for behavioral events.

Core event types:

- impression
- click
- view
- watch_progress
- completion
- skip
- rewatch
- like
- dislike
- comment
- share
- bookmark
- follow
- unfollow
- search
- profile_view
- not_interested
- mute_topic
- mute_creator
- report

Each event should contain a stable event ID, user ID or privacy-safe actor reference, content ID, event type, event timestamp, client/server timestamps where useful, and schema version. Validate events server-side.

## 2. Core data structures

### User interest profile

Sparse map:

`topic_id -> InterestState`

Where `InterestState` contains:

- score
- confidence
- positive_count
- negative_count
- last_updated
- decay_version

Do not allocate a dense vector for every possible topic unless measurement justifies it.

### Content feature profile

`content_id -> ContentFeatures`

Features may include:

- topic IDs
- language
- media type
- creator ID
- freshness timestamp
- quality score
- safety/eligibility state
- engagement-quality statistics

### Candidate set

Use a bounded vector/array of candidate IDs with source labels and generation scores.

Example sources:

- following
- topic affinity
- creator affinity
- collaborative similarity
- trending
- fresh
- exploration

### Feed cache

Use Redis sorted sets/lists or another measured structure suitable for ordered candidate IDs. Keep persistent truth in PostgreSQL/event storage.

### Negative feedback set

Use compact keyed sets for:

- blocked creators
- muted creators
- muted topics
- not-interested content

Apply TTLs where product semantics permit them.

## 3. Interest update algorithm

Start with a deterministic weighted model.

Positive and negative signals have different weights. Stronger signals include high-quality completion, rewatch, meaningful follow, bookmark, and share. Negative signals include rapid skip, explicit dislike, not-interested, mute, and report.

Apply time decay so old behavior loses influence. Do not treat one event as a permanent preference.

Keep weights in versioned configuration rather than hard-coding them into controllers.

## 4. Candidate generation

Do not rank the entire corpus.

Pipeline:

`large corpus -> candidate generators -> bounded candidate set -> feature hydration -> ranking -> diversity -> safety -> feed`

Each generator must have a maximum candidate budget and timeout.

## 5. Ranking

Initial implementation: weighted deterministic scoring.

Ranking signals:

- user-topic affinity
- creator affinity
- content similarity
- recency
- predicted engagement quality
- watch/completion behavior
- negative feedback
- freshness
- content quality

Do not optimize only for raw engagement or session length.

Keep the ranking interface model-agnostic so a trained model can replace deterministic scoring later.

## 6. Diversity

Avoid returning near-duplicate content or too many posts from one creator/topic.

Use a re-ranking stage after base ranking to enforce:

- creator diversity
- topic diversity
- media diversity
- freshness diversity

## 7. Exploration vs exploitation

Reserve a controlled portion of recommendation capacity for exploration of new creators/topics. Exploration must respect safety, privacy, and user controls.

Use deterministic guardrails before any probabilistic exploration strategy.

## 8. Anti-abuse scoring

Do not trust raw likes/views/shares.

Maintain separate quality signals for:

- unique users
- account age/quality
- suspicious coordination
- bot probability
- repeated engagement
- abnormal watch patterns
- spam reports

Anti-abuse scores should affect eligibility/ranking without silently becoming a user's personal-interest score.

## 9. Algorithms to support later

The architecture should allow these components to be added without changing API contracts:

- collaborative filtering
- content-based retrieval
- approximate nearest-neighbor retrieval
- learning-to-rank
- pairwise/listwise ranking
- embedding-based retrieval
- contextual bandits for controlled exploration
- graph-based recommendation

Do not add ML infrastructure until baseline metrics exist.

## 10. Complexity targets

Target approximately:

- event ingestion: O(1) append/queue operation
- interest update: O(k), where k is the small number of affected topics/features
- candidate merge: O(C log S) or equivalent bounded implementation
- top-K selection: O(C log K) where appropriate
- diversity re-ranking: O(K * D) with small bounded K/D

All complexity claims must be validated against the actual implementation and workload.

## 11. Metrics

Offline:

- precision@K
- recall@K
- NDCG@K
- coverage
- creator diversity
- topic diversity
- novelty
- calibration

Online:

- meaningful engagement
- completion rate
- negative feedback rate
- report rate
- retention
- feed latency P50/P95/P99
- recommendation coverage

Do not optimize retention or session duration as a sole objective.

## 12. Privacy requirements

Behavioral data must have purpose limitation, retention rules, access controls, deletion workflows, and auditability. Recommendation features must not be used for authentication, authorization, or security decisions.

## 13. Implementation rule

Every algorithm must have:

1. Unit tests with deterministic fixtures.
2. Benchmark/load tests for hot paths.
3. Versioned configuration.
4. Metrics.
5. Safe fallback behavior.
6. Documentation of assumptions and complexity.

Never claim a recommendation algorithm is production-ready without benchmark and safety evidence.
