SELECT title, rating from movies INNER JOIN ratings ON movie_id = id
WHERE year = "2010"
ORDER BY rating DESC, title ASC