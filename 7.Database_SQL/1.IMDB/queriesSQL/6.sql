SELECT AVG(rating)
FROM ratings
JOIN movies ON movie_id = id
WHERE movies.year = 2012;