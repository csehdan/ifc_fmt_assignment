# Assignment: IFC `DATA` Section Formatter (C++)

## Timebox
4–6 hours.

## What you get
A repository containing:
- an empty CMake project (`CMakeLists.txt`, `main.cpp`)
- `README.md` (this assignment)
- `data/` with 3 IFC STEP Part 21 samples
  - `sample_01.ifc`
  - `sample_02.ifc`
  - `sample_03.ifc`

## Objective
Create a command-line tool that rewrites the `DATA; ... ENDSEC;` section of an IFC STEP Part 21 file into a stable canonical form.

This is a **formatting** task. You are not expected to validate IFC schema, resolve references, or interpret geometry.

## CLI
Build an executable (name is up to you) that supports:

```text
ifc_fmt <input.ifc> <output.ifc>
```

Return codes:
- `0` on success
- non-zero on failure (print a brief error message to `stderr`)

## Canonical formatting (applies only inside `DATA; ... ENDSEC;`)
For every entity instance statement in the DATA section, output:

- **Exactly one statement per line**
- **No leading/trailing whitespace** on the line
- **No whitespace outside string literals**
- Preserve the content of **string literals** byte-for-byte
- Do not normalize numeric spellings (keep `1.E-05` as-is)

Target line shape:

```step
#12=IFCGEOMETRICREPRESENTATIONCONTEXT($,'Model',3,1.E-05,#11,$);
```

Notes:
- An “entity instance statement” is any DATA section statement that ends with `;`.
- Your formatter must not change characters inside STEP strings (`'...'`) including escaped apostrophes represented as `''`.

## File handling outside `DATA`
Everything outside the `DATA; ... ENDSEC;` section must be preserved.

Acceptable approaches:
- Copy non-DATA content verbatim (preferred).
- Or re-emit it in a way that keeps the file valid STEP Part 21 and semantically unchanged.

## Correctness requirements
Your tool must handle the following (present in provided samples):

- arbitrary whitespace and newlines between tokens in DATA
- multiple statements on a single physical line
- nested parentheses (aggregates)
- STEP strings with escaped apostrophes (`''`)
- enums/logicals like `.ADDED.`, `.T.`, `.F.`, `.U.`
- typed values that look like `IDENTIFIER(<params>)` (treat them as ordinary tokens)

## Failure cases (minimum)
Fail with non-zero exit code if:
- `DATA;` is missing
- `ENDSEC;` after `DATA;` is missing
- the DATA section contains a statement that is not terminated before EOF
- a string literal is not terminated before EOF
- parentheses nesting becomes invalid (e.g., more `)` than `(`. Not applicable to strings) 

(If you can report line/column, do so; not required.)

## Example
Formatted data section of `sample_01.ifc` should look like this:
```ifc
#1=IFCPERSON($,$,'Jo''nas',$,$,$,$,$);
#2=IFCORGANIZATION($,'Org',$,$,$);
#3=IFCPERSONANDORGANIZATION(#1,#2,$);
#4=IFCAPPLICATION(#2,'1.0','App','AppId');
#5=IFCOWNERHISTORY(#3,#4,$,.ADDED.,$,$,$,0);
#6=IFCSIUNIT(*,.LENGTHUNIT.,$,.METRE.);
#7=IFCSIUNIT(*,.AREAUNIT.,$,.SQUARE_METRE.);
#8=IFCSIUNIT(*,.VOLUMEUNIT.,$,.CUBIC_METRE.);
#9=IFCUNITASSIGNMENT((#6,#7,#8));
#10=IFCCARTESIANPOINT((0.,0.,0.));
#11=IFCAXIS2PLACEMENT3D(#10,$,$);
#12=IFCGEOMETRICREPRESENTATIONCONTEXT($,'Model',3,1.E-05,#11,$);
#13=IFCPROJECT('0$7jH1N1H9Qf8O2rK5jE1',#5,'P1',$,$,$,$,(#12),#9);
#14=IFCLOCALPLACEMENT($,#11);
#15=IFCSITE('1$7jH1N1H9Qf8O2rK5jE2',#5,'SITE',$,$,#14,$,$,.ELEMENT.,$,$,$,$,$);
#16=IFCRELAGGREGATES('2$7jH1N1H9Qf8O2rK5jE3',#5,$,$,#13,(#15));
```

## Tests (preferably Catch2)
Add automated tests. Catch2 is preferred.

Minimum expectations:
- at least 4 unit tests covering:
  1) whitespace removal outside strings
  2) strings preserved exactly (including `''`)
  3) nested parentheses handled correctly
  4) multiple statements on one line become one-per-line

Recommended:
- “golden file” tests comparing the full formatted output of each provided sample to expected outputs.
- idempotence check: formatting output again yields identical output.

## Deliverables
- source code
- tests
- `DESIGN.md` (short):
  - build and test instructions
  - approach at a high level
  - assumptions
  - limitations / non-goals
  - what you would do next with more time

## Non-goals (explicit)
- No IFC schema compliance validation
- No reference resolution
- No geometry/placement evaluation
- No unit conversion

## Evaluation criteria
- correctness on provided samples and additional unseen fixtures
- deterministic output and idempotence
- code readability and structure
- test quality and coverage