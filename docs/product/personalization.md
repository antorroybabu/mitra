# Personalization

MITRA should learn user interests from explicit signals (follow, like, bookmark, not-interested, topic choices) and bounded implicit signals (impression, watch time, completion, skip, rewatch, share).

Use time decay so old behavior does not permanently define a user. Store only data necessary for product purposes, enforce access controls, and provide user controls such as Not Interested and mute topic/creator.

Pipeline:

Event -> Redpanda/Kafka -> behavior service -> feature/interest model -> candidate generation -> ranking -> diversity -> safety/moderation -> feed cache.

The ranking system must optimize for user value and healthy engagement, not compulsive or deceptive behavior. Keep a clean interface so a learned ranking model can replace the initial rules-based scorer later.
