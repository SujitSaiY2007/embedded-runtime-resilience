# Post-K.10 Research & Development Plan

This is the canonical planning artifact for the sequence after K.10 and before/through the final software demonstration.

## Canonical sequence

**K.10 COMPLETE**

1. **K.10.1 — Adversarial Prior-Art & Feature-Distinction Review**
2. **K.10.2 — Deep Single-Reference Anticipation Review**
3. **K.10.3 — Multi-Reference Combination & Technical Obviousness Analysis**
4. **K.10.4 — Final Technical Distinction & Research Conclusion**
5. **K.11 — Final Software Synthesis + Hardware-Validation Handoff**
6. **K.12 — Final Software Productization + Clean UI Demonstration**
7. **Final exp audit**
8. **Validated synchronization to main**

## K.10.1

Attack the remaining technical distinction. Build the complete P4 feature/limitation matrix, map it against strong prior art, search for adversarial references, and identify genuine remaining distinctions.

No P4 redesign. No new policy. No hardware. No legal patentability opinion.

## K.10.2

Perform a deep single-reference analysis. For every strongest reference, establish exactly which P4 limitations are disclosed, which are absent, and which would require inference.

The key question is whether one reference actually discloses the complete relevant combination.

## K.10.3

Perform multi-reference combination analysis. Identify the strongest combinations that could challenge the remaining distinction, the technical teaching supplied by each reference, the compatibility of the combination, and any missing technical step or interaction.

This is technical research, not a legal opinion.

## K.10.4

Integrate K.10 experimental evidence with K.10.1-K.10.3. Produce the final evidence-bounded technical-distinction conclusion, including residual risks and limitations.

Do not force a positive conclusion.

## K.11

Package the final software research conclusion, architecture, evidence, limitations, and target-MCU validation handoff. No physical hardware validation is claimed unless separately executed and authorized.

## K.12

Finalize the software product/demo layer after the research conclusion is frozen. Clean the UI, reconcile terminology, ensure evidence traceability, verify the authoritative runtime path, run final checks, and produce the complete professor-facing software demonstration.

K.12 must not change the research mechanism merely to improve presentation.

## ChatGPT / Antigravity governance

ChatGPT owns the sequence and checkpoint boundaries.

Antigravity is an execution agent only inside the current ChatGPT-defined checkpoint. It may run repository operations, experiments, searches, tests, and documentation updates that are explicitly authorized by that checkpoint.

Antigravity must never:
- create a new chat-wise roadmap;
- renumber checkpoints;
- advance into a later checkpoint;
- redesign P4 outside the authorized scope.

Every ChatGPT checkpoint must close with:
- exact branch/SHA state;
- changed files;
- validation;
- unresolved issues;
- scope boundary;
- the complete continuation prompt for the next ChatGPT chat.

## Branch governance

`exp` is the active research/integration branch.

`main` is the integrated stable mirror and is synchronized only after a checkpoint is validated and explicitly closed.

Historical child branches remain available as provenance. They are not active roadmap authorities.

## Finalization rule

The research phase is not considered closed immediately after K.10. K.10.1-K.10.4 must attack and resolve the remaining technical-distinction question first. K.11 then packages the final software conclusion. K.12 produces the final clean software demonstration.
