SELECT DISTINCT(name)
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE people.name NOT LIKE 'Kevin Bacon' AND movies.title IN (
    SELECT title
    FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE people.name LIKE 'Kevin Bacon' AND people.birth = 1958
);