from keras.datasets import imdb

(train_data, train_labels), (test_data, test_labels) = imdb.load_data(num_words=10000)

dictionary=dict([(v,k) for (k,v) in imdb.get_word_index().items()]) 

review = train_data[0]

review_decoded = [dictionary.get(i - 3, '?') for i in review]
text = ' '.join(review_decoded)
print(text)
