SELECT name, birth
FROM people
WHERE id IN (
    SELECT person_id
    FROM stars
    JOIN movies_id IN (
    SELECT id
    FROM movies
    WHERE year = 2004
    )
)
ORDER BY birth;
