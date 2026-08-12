# User Service

Owns user profile and account-domain data exposed through authorized APIs.

Responsibilities:

- User profile lifecycle
- Public profile metadata
- Account status
- User preferences
- Privacy settings
- Soft-delete/deletion workflow coordination

Authentication credentials remain owned by Auth Service. Recommendation and behavioral systems must not become an authorization source.
