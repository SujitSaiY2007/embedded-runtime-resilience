# Project Manual

## 1. Purpose

This repository is the canonical working record for a solo, software-based embedded-systems research project focused on **missed opportunities in simpler areas of embedded systems**.

The intended outcome is not merely a functioning application. The target is a technically defensible research contribution that may support an academic publication and, if the evidence warrants it, a patent filing.

## 2. Research philosophy

The project begins with a problem-space hypothesis, not a predetermined invention.

We will actively try to disprove promising ideas by checking:

- peer-reviewed papers;
- conference proceedings;
- theses and technical reports;
- patents and patent applications;
- standards and specifications;
- commercial products;
- open-source implementations;
- archived documentation and historical solutions where relevant.

A feature being uncommon is not sufficient evidence of novelty.

## 3. Required evidence before topic freeze

For the final candidate we must be able to state:

1. What existing systems already do.
2. What existing systems fail to do or do inefficiently.
3. Why that limitation matters in a realistic embedded setting.
4. Why the proposed mechanism is technically different from known approaches.
5. Which prior-art references are closest.
6. What remains uncertain.
7. How the proposed contribution can be experimentally tested.

## 4. Patent-awareness rule

Potentially patent-relevant implementation details should not be unnecessarily published in issues, discussions, README files, screenshots, or public documentation before an IP decision is made.

This repository may ultimately be public, so sensitive invention details must be separated deliberately from public-facing material.

## 5. Development model

Use controlled, traceable increments:

`research -> hypothesis -> falsification -> design -> prototype -> experiment -> evaluation -> revision`

Avoid premature implementation. Code should follow a validated technical hypothesis rather than substitute for one.

## 6. Git workflow

Recommended branch classes:

- `research/<topic>` — research exploration
- `design/<component>` — architecture/design work
- `feature/<component>` — implementation
- `experiment/<name>` — reproducible experiments
- `docs/<area>` — documentation

The `main` branch should represent the most defensible integrated state.

Use focused commits with messages that describe the actual change.

## 7. Continuity protocol

Every major session should update:

- `PROJECT_STATE.md` — current state and gates;
- `CURRENT_HANDOFF.md` — exact continuation point;
- `DECISION_LOG.md` — consequential decisions and rejected alternatives;
- research records — new evidence and source assessments.

A future chat must be able to reconstruct the project from these files without relying on the old conversation.

## 8. Quality gates

No candidate becomes the final topic until it passes all of the following:

- relevance to software-based embedded systems;
- meaningful problem rather than artificial complexity;
- credible missed opportunity;
- evidence of a defensible research gap;
- manageable solo implementation scope;
- measurable technical contribution;
- reproducible evaluation;
- sufficiently differentiated prior art;
- plausible publication value;
- plausible patentability pathway, subject to professional patent assessment.

## 9. Patent disclaimer

A project being described as “potentially patentable” is not a legal conclusion. Patentability depends on jurisdiction, claim construction, prior art, disclosure timing, inventorship, and professional legal assessment.
