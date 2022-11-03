dpl ?= deploy.env
include $(dpl)
export $(shell sed 's/=.*//' $(dpl))

build: ## Build the container
		docker build --tag $(DOCKER_NAME) .
		docker tag $(DOCKER_NAME) $(DOCKER_REPO)/$(DOCKER_NAME):$(VERSION)

run: ## Run container on port configured in `config.env`
		docker run -it -v $(PWD)/..:/workspace $(DOCKER_NAME)

stop: ## Stop and remove a running container
		docker stop $(DOCKER_NAME) ; docker rm $(DOCKER_NAME)

push: ## Push container
		docker push  ${DOCKER_REPO}/$(DOCKER_NAME):$(VERSION)
