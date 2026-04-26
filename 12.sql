SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Bradley Cooper'
AND movies.id IN (
    SELECT movie_id FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Jennifer Lawrence'
);
